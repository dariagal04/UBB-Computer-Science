namespace MagazineCosmeticeApp
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGridViewMagazine = new System.Windows.Forms.DataGridView();
            this.dataGridViewAngajati = new System.Windows.Forms.DataGridView();
            this.textBoxNume = new System.Windows.Forms.TextBox();
            this.textBoxFunctie = new System.Windows.Forms.TextBox();
            this.insertButton = new System.Windows.Forms.Button();
            this.deleteButton = new System.Windows.Forms.Button();
            this.reloadButton = new System.Windows.Forms.Button();
            this.back_button = new System.Windows.Forms.Button();
            this.labelNume = new System.Windows.Forms.Label();
            this.labelFunctie = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewMagazine)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewAngajati)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewMagazine
            // 
            this.dataGridViewMagazine.BackgroundColor = System.Drawing.SystemColors.ActiveCaption;
            this.dataGridViewMagazine.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewMagazine.Location = new System.Drawing.Point(0, 0);
            this.dataGridViewMagazine.Name = "dataGridViewMagazine";
            this.dataGridViewMagazine.RowHeadersWidth = 51;
            this.dataGridViewMagazine.RowTemplate.Height = 24;
            this.dataGridViewMagazine.Size = new System.Drawing.Size(266, 245);
            this.dataGridViewMagazine.TabIndex = 0;
            // 
            // dataGridViewAngajati
            // 
            this.dataGridViewAngajati.BackgroundColor = System.Drawing.SystemColors.ActiveCaption;
            this.dataGridViewAngajati.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewAngajati.Location = new System.Drawing.Point(266, 0);
            this.dataGridViewAngajati.Name = "dataGridViewAngajati";
            this.dataGridViewAngajati.RowHeadersWidth = 51;
            this.dataGridViewAngajati.RowTemplate.Height = 24;
            this.dataGridViewAngajati.Size = new System.Drawing.Size(431, 245);
            this.dataGridViewAngajati.TabIndex = 1;
            // 
            // textBoxNume
            // 
            this.textBoxNume.Location = new System.Drawing.Point(98, 286);
            this.textBoxNume.Multiline = true;
            this.textBoxNume.Name = "textBoxNume";
            this.textBoxNume.Size = new System.Drawing.Size(156, 34);
            this.textBoxNume.TabIndex = 2;
            // 
            // textBoxFunctie
            // 
            this.textBoxFunctie.Location = new System.Drawing.Point(410, 283);
            this.textBoxFunctie.Multiline = true;
            this.textBoxFunctie.Name = "textBoxFunctie";
            this.textBoxFunctie.Size = new System.Drawing.Size(170, 34);
            this.textBoxFunctie.TabIndex = 3;
            // 
            // insertButton
            // 
            this.insertButton.Location = new System.Drawing.Point(98, 377);
            this.insertButton.Name = "insertButton";
            this.insertButton.Size = new System.Drawing.Size(120, 66);
            this.insertButton.TabIndex = 4;
            this.insertButton.Text = "insert";
            this.insertButton.UseVisualStyleBackColor = true;
            this.insertButton.Click += new System.EventHandler(this.insertButton_Click);
            // 
            // deleteButton
            // 
            this.deleteButton.Location = new System.Drawing.Point(266, 377);
            this.deleteButton.Name = "deleteButton";
            this.deleteButton.Size = new System.Drawing.Size(121, 66);
            this.deleteButton.TabIndex = 5;
            this.deleteButton.Text = "delete";
            this.deleteButton.UseVisualStyleBackColor = true;
            this.deleteButton.Click += new System.EventHandler(this.deleteButton_Click);
            // 
            // reloadButton
            // 
            this.reloadButton.Location = new System.Drawing.Point(436, 377);
            this.reloadButton.Name = "reloadButton";
            this.reloadButton.Size = new System.Drawing.Size(118, 66);
            this.reloadButton.TabIndex = 6;
            this.reloadButton.Text = "reload";
            this.reloadButton.UseVisualStyleBackColor = true;
            // 
            // back_button
            // 
            this.back_button.Location = new System.Drawing.Point(0, 514);
            this.back_button.Name = "back_button";
            this.back_button.Size = new System.Drawing.Size(75, 23);
            this.back_button.TabIndex = 7;
            this.back_button.Text = "back";
            this.back_button.UseVisualStyleBackColor = true;
            this.back_button.Click += new System.EventHandler(this.back_button_Click);
            // 
            // labelNume
            // 
            this.labelNume.AutoSize = true;
            this.labelNume.Location = new System.Drawing.Point(127, 267);
            this.labelNume.Name = "labelNume";
            this.labelNume.Size = new System.Drawing.Size(40, 16);
            this.labelNume.TabIndex = 8;
            this.labelNume.Text = "nume";
            // 
            // labelFunctie
            // 
            this.labelFunctie.AutoSize = true;
            this.labelFunctie.Location = new System.Drawing.Point(433, 264);
            this.labelFunctie.Name = "labelFunctie";
            this.labelFunctie.Size = new System.Drawing.Size(45, 16);
            this.labelFunctie.TabIndex = 9;
            this.labelFunctie.Text = "functie";
            // 
            // Form1
            // 
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(696, 549);
            this.Controls.Add(this.labelFunctie);
            this.Controls.Add(this.labelNume);
            this.Controls.Add(this.back_button);
            this.Controls.Add(this.reloadButton);
            this.Controls.Add(this.deleteButton);
            this.Controls.Add(this.insertButton);
            this.Controls.Add(this.textBoxFunctie);
            this.Controls.Add(this.textBoxNume);
            this.Controls.Add(this.dataGridViewAngajati);
            this.Controls.Add(this.dataGridViewMagazine);
            this.Name = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewMagazine)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewAngajati)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
        #endregion


        private System.Windows.Forms.DataGridView dataGridViewMagazine;
        private System.Windows.Forms.DataGridView dataGridViewAngajati;
        private System.Windows.Forms.TextBox textBoxNume;
        private System.Windows.Forms.TextBox textBoxFunctie;
        private System.Windows.Forms.Button insertButton;
        private System.Windows.Forms.Button deleteButton;
        private System.Windows.Forms.Button reloadButton;
        private System.Windows.Forms.Button back_button;
        private System.Windows.Forms.Label labelNume;
        private System.Windows.Forms.Label labelFunctie;
    }

}