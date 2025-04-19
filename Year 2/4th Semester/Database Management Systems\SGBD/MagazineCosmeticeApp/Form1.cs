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

namespace MagazineCosmeticeApp
{
    public partial class Form1 : Form
    {
        private DataSet _ds = new DataSet();
        private SqlDataAdapter magazineAdapter;
        private SqlDataAdapter angajatiAdapter;
        private BindingSource bsMagazine = new BindingSource();
        private BindingSource bsAngajati = new BindingSource();
        string connectionString = @"Server=ASUS-PC\SQLEXPRESS;Database=MagazineCosmetice;Integrated Security=true;TrustServerCertificate=True;";

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

                    magazineAdapter = new SqlDataAdapter("SELECT * FROM Magazine", conn);
                    angajatiAdapter = new SqlDataAdapter("SELECT * FROM Angajati", conn);

                    magazineAdapter.Fill(_ds, "Magazine");
                    angajatiAdapter.Fill(_ds, "Angajati");

                    DataColumn pkColumn = _ds.Tables["Magazine"].Columns["Mid"];
                    DataColumn fkColumn = _ds.Tables["Angajati"].Columns["MagazinID"];
                    DataRelation relation = new DataRelation("FK_Magazin_Angajati", pkColumn, fkColumn, true);
                    _ds.Relations.Add(relation);

                    bsMagazine.DataSource = _ds.Tables["Magazine"];
                    dataGridViewMagazine.DataSource = bsMagazine;

                    bsAngajati.DataSource = bsMagazine;
                    bsAngajati.DataMember = "FK_Magazin_Angajati";
                    dataGridViewAngajati.DataSource = bsAngajati;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void reloadButton_Click()
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();
                angajatiAdapter = new SqlDataAdapter("SELECT * FROM Angajati", conn);
                _ds.Tables["Angajati"]?.Clear();
                angajatiAdapter.Fill(_ds, "Angajati");
            }
        }

        private void insertButton_Click(object sender, EventArgs e)
        {
            if (textBoxNume.Text.Length > 0 && textBoxFunctie.Text.Length > 0)
            {
                try
                {
                    int selectedMagazinId = (int)dataGridViewMagazine.CurrentRow.Cells["Mid"].Value;

                    using (SqlConnection conn = new SqlConnection(connectionString))
                    {
                        conn.Open();
                        SqlCommand cmd = new SqlCommand("INSERT INTO Angajati (NumeAngajat, Functie, MagazinID) VALUES (@nume, @functie, @magazinID)", conn);
                        cmd.Parameters.AddWithValue("@nume", textBoxNume.Text);
                        cmd.Parameters.AddWithValue("@functie", textBoxFunctie.Text);
                        cmd.Parameters.AddWithValue("@magazinID", selectedMagazinId);
                        cmd.ExecuteNonQuery();

                        MessageBox.Show("Angajat adăugat cu succes.");
                        textBoxNume.Clear();
                        textBoxFunctie.Clear();
                        reloadButton_Click();
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
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
                int angajatId = (int)dataGridViewAngajati.CurrentRow.Cells["Aid"].Value;

                try
                {
                    using (SqlConnection conn = new SqlConnection(connectionString))
                    {
                        conn.Open();
                        SqlCommand cmd = new SqlCommand("DELETE FROM Angajati WHERE Aid = @id", conn);
                        cmd.Parameters.AddWithValue("@id", angajatId);
                        cmd.ExecuteNonQuery();

                        MessageBox.Show("Angajat șters cu succes.");
                        reloadButton_Click();
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Eroare la ștergere: " + ex.Message);
                }
            }
            else
            {
                MessageBox.Show("Selectează un angajat pentru a-l șterge.");
            }
        }

        private void back_button_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(connectionString))
                {
                    conn.Open();
                    angajatiAdapter = new SqlDataAdapter("SELECT * FROM Angajati", conn);
                    _ds.Tables["Angajati"]?.Clear();
                    angajatiAdapter.Fill(_ds, "Angajati");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

       
    }
}