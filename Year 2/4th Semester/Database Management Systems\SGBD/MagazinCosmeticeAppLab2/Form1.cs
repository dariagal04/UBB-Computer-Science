using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Configuration; // Necesitar pentru ConfigurationManager

namespace MagazineCosmeticeAppLab2
{
    public partial class Form1 : Form
    {
        private DataSet _ds = new DataSet();
        private SqlDataAdapter masterAdapter;
        private SqlDataAdapter detailAdapter;
        private BindingSource bsMaster = new BindingSource();
        private BindingSource bsDetail = new BindingSource();
        string connectionString = ConfigurationManager.ConnectionStrings["DefaultConnection"].ConnectionString;

        // Citim setările din App.config
        string masterTable = ConfigurationManager.AppSettings["MasterTable"];
        string detailTable = ConfigurationManager.AppSettings["DetailTable"];
        string masterPrimaryKey = ConfigurationManager.AppSettings["MasterPrimaryKey"];
        string detailForeignKey = ConfigurationManager.AppSettings["DetailForeignKey"];
        string masterSelectQuery = ConfigurationManager.AppSettings["MasterSelectQuery"];
        string detailSelectQuery = ConfigurationManager.AppSettings["DetailSelectQuery"];
        string detailInsertQuery = ConfigurationManager.AppSettings["DetailInsertQuery"];
        string detailDeleteQuery = ConfigurationManager.AppSettings["DetailDeleteQuery"];
        string detailFields = ConfigurationManager.AppSettings["DetailFields"];

        public Form1()
        {
            InitializeComponent();
            this.Load += Form1_Load;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(connectionString))
                {
                    conn.Open();

                    // Creăm adaptori pentru tabelele citite din App.config
                    masterAdapter = new SqlDataAdapter(masterSelectQuery, conn);
                    detailAdapter = new SqlDataAdapter(detailSelectQuery, conn);

                    // Umplem DataSet-ul
                    masterAdapter.Fill(_ds, masterTable);
                    detailAdapter.Fill(_ds, detailTable);

                    // Creăm relația dintre tabele
                    DataColumn pkColumn = _ds.Tables[masterTable].Columns[masterPrimaryKey];
                    DataColumn fkColumn = _ds.Tables[detailTable].Columns[detailForeignKey];
                    DataRelation relation = new DataRelation($"FK_{masterTable}_{detailTable}", pkColumn, fkColumn, true);
                    _ds.Relations.Add(relation);

                    bsMaster.DataSource = _ds.Tables[masterTable];
                    dataGridViewMagazine.DataSource = bsMaster;

                    bsDetail.DataSource = bsMaster;
                    bsDetail.DataMember = $"FK_{masterTable}_{detailTable}";
                    dataGridViewAngajati.DataSource = bsDetail;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void reloadButton_Click(object sender, EventArgs e)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();
                detailAdapter = new SqlDataAdapter(detailSelectQuery, conn);
                _ds.Tables[detailTable]?.Clear();
                detailAdapter.Fill(_ds, detailTable);
            }
        }

        private void insertButton_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(textBoxNume.Text) && !string.IsNullOrEmpty(textBoxFunctie.Text))
            {
                try
                {
                    // Get selected master record id
                    int selectedMasterId = (int)dataGridViewMagazine.CurrentRow.Cells[masterPrimaryKey].Value;

                    // Split fields from the configuration to dynamically add parameters
                    string[] fields = detailFields.Split(',');

                    using (SqlConnection conn = new SqlConnection(connectionString))
                    {
                        conn.Open();

                        // Create command with dynamic insert query
                        SqlCommand cmd = new SqlCommand(detailInsertQuery, conn);

                        // Add parameters dynamically based on the fields provided
                        for (int i = 0; i < fields.Length; i++)
                        {
                            string paramName = "@" + fields[i];
                            string paramValue = (i == 0) ? textBoxNume.Text : textBoxFunctie.Text;
                            cmd.Parameters.AddWithValue(paramName, paramValue);
                        }
                        cmd.Parameters.AddWithValue("@masterId", selectedMasterId);

                        // Execute the insert command
                        cmd.ExecuteNonQuery();

                        MessageBox.Show("Inserare reușită.");
                        textBoxNume.Clear();
                        textBoxFunctie.Clear();

                        // Reload data after insertion
                        reloadButton_Click(sender, e);
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Eroare la inserare: {ex.Message}");
                }
            }
            else
            {
                MessageBox.Show("Completează toate câmpurile.");
            }
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            if (dataGridViewAngajati.CurrentRow != null)
            {
                try
                {
                    // Get the selected detail record id
                    int selectedDetailId = (int)dataGridViewAngajati.CurrentRow.Cells[0].Value;

                    using (SqlConnection conn = new SqlConnection(connectionString))
                    {
                        conn.Open();
                        // Create and execute delete command
                        SqlCommand cmd = new SqlCommand(detailDeleteQuery, conn);
                        cmd.Parameters.AddWithValue("@id", selectedDetailId);

                        cmd.ExecuteNonQuery();
                        MessageBox.Show("Ștergere reușită.");

                        // Reload data after deletion
                        reloadButton_Click(sender, e);
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Eroare la ștergere: {ex.Message}");
                }
            }
            else
            {
                MessageBox.Show("Selectează o înregistrare pentru ștergere.");
            }
        }


    }
}
