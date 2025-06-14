using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace InghetataCofetarieApp
{
    public partial class Form1 : Form
    {
        private DataSet _ds = new DataSet();
        private SqlDataAdapter cofetariiAdapter;
        private SqlDataAdapter inghetateAdapter;
        private BindingSource bsCofetarii = new BindingSource();
        private BindingSource bsInghetate = new BindingSource();

        string connectionString = @"Server=ASUS-PC\SQLEXPRESS;Database=InghetataCofetarie;Integrated Security=true;TrustServerCertificate=True;";

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

                    cofetariiAdapter = new SqlDataAdapter("SELECT * FROM Cofetarii", conn);
                    inghetateAdapter = new SqlDataAdapter("SELECT * FROM Inghetate", conn);
                    

                    cofetariiAdapter.Fill(_ds, "Cofetarii");
                    inghetateAdapter.Fill(_ds, "Inghetate");

                    DataColumn pkColumn = _ds.Tables["Cofetarii"].Columns["cod"];
                    DataColumn fkColumn = _ds.Tables["Inghetate"].Columns["cod_cofetarie"];
                    DataRelation relation = new DataRelation("FK_Cofetarie_Inghetate", pkColumn, fkColumn, true);
                    _ds.Relations.Add(relation);

                    bsCofetarii.DataSource = _ds.Tables["Cofetarii"];
                    dataGridViewCofetarii.DataSource = bsCofetarii;

                    bsInghetate.DataSource = bsCofetarii;
                    bsInghetate.DataMember = "FK_Cofetarie_Inghetate";
                    dataGridViewInghetate.DataSource = bsInghetate;
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
                inghetateAdapter = new SqlDataAdapter("SELECT * FROM Inghetate", conn);
                _ds.Tables["Inghetate"]?.Clear();
                inghetateAdapter.Fill(_ds, "Inghetate");
            }
        }

        private void insertButton_Click(object sender, EventArgs e)
        {
            if (textBoxNume.Text.Length > 0 && textBoxIngrediente.Text.Length > 0 && decimal.TryParse(textBoxVanzari.Text, out decimal vanzari))
            {
                try
                {
                    string selectedCofetarieCod = dataGridViewCofetarii.CurrentRow.Cells["cod"].Value.ToString();

                    using (SqlConnection conn = new SqlConnection(connectionString))
                    {
                        conn.Open();
                        SqlCommand cmd = new SqlCommand("INSERT INTO Inghetate (cod, nume, ingrediente, valoare_vanzari_an_precedent, cod_cofetarie) " +
                                                        "VALUES (@cod, @nume, @ingrediente, @vanzari, @cofetarieCod)", conn);
                        cmd.Parameters.AddWithValue("@cod", Guid.NewGuid().ToString().Substring(0, 8));
                        cmd.Parameters.AddWithValue("@nume", textBoxNume.Text);
                        cmd.Parameters.AddWithValue("@ingrediente", textBoxIngrediente.Text);
                        cmd.Parameters.AddWithValue("@vanzari", vanzari);
                        cmd.Parameters.AddWithValue("@cofetarieCod", selectedCofetarieCod);
                        cmd.ExecuteNonQuery();

                        MessageBox.Show("Înghețată adăugată cu succes.");
                        textBoxNume.Clear();
                        textBoxIngrediente.Clear();
                        textBoxVanzari.Clear();
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
                MessageBox.Show("Completează toate câmpurile corect.");
            }
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            if (dataGridViewInghetate.CurrentRow != null)
            {
                string inghetataCod = dataGridViewInghetate.CurrentRow.Cells["cod"].Value.ToString();

                try
                {
                    using (SqlConnection conn = new SqlConnection(connectionString))
                    {
                        conn.Open();
                        SqlCommand cmd = new SqlCommand("DELETE FROM Inghetate WHERE cod = @cod", conn);
                        cmd.Parameters.AddWithValue("@cod", inghetataCod);
                        cmd.ExecuteNonQuery();

                        MessageBox.Show("Înghețată ștearsă cu succes.");
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
                MessageBox.Show("Selectează o înghețată pentru a o șterge.");
            }
        }

        private void reloadButton_Click(object sender, EventArgs e)
        {
            if (textBoxNume.Text.Length > 0 && textBoxIngrediente.Text.Length > 0 && decimal.TryParse(textBoxVanzari.Text, out decimal vanzari))
            {
                try
                {
                    string selectedCofetarieCod = dataGridViewCofetarii.CurrentRow.Cells["cod"].Value.ToString();

                    using (SqlConnection conn = new SqlConnection(connectionString))
                    {
                        conn.Open();
                        string query = "UPDATE Inghetate " +
                                       "SET nume = @nume, " +
                                       "ingrediente = @ingrediente, " +
                                       "valoare_vanzari_an_precedent = @vanzari, " +
                                       "cod_cofetarie = @cofetarieCod " +
                                       "WHERE cod = @cod";

                        using (SqlCommand cmd = new SqlCommand(query, conn))
                        {
                            cmd.Parameters.AddWithValue("@cod", Guid.NewGuid().ToString().Substring(0, 8));
                            cmd.Parameters.AddWithValue("@nume", textBoxNume.Text);
                            cmd.Parameters.AddWithValue("@ingrediente", textBoxIngrediente.Text);
                            cmd.Parameters.AddWithValue("@vanzari", vanzari);
                            cmd.Parameters.AddWithValue("@cofetarieCod", selectedCofetarieCod);

                            int rowsAffected = cmd.ExecuteNonQuery();
                            if (rowsAffected == 0)
                            {
                                MessageBox.Show("Nicio înghețată nu a fost actualizată. Verifică codul!");
                            }
                            else
                            {
                                MessageBox.Show("Înghețata a fost actualizată cu succes!");
                            }
                        }
                    }

                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            else
            {
                MessageBox.Show("Completează toate câmpurile corect.");
            }
        }

        private void textBoxNume_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
