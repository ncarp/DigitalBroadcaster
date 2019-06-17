namespace BroadcasterReporting
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
            this.components = new System.ComponentModel.Container();
            Microsoft.Reporting.WinForms.ReportDataSource reportDataSource1 = new Microsoft.Reporting.WinForms.ReportDataSource();
            this.ViewERCBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.OnAirDataSet = new BroadcasterReporting.OnAirDataSet();
            this.reportViewer1 = new Microsoft.Reporting.WinForms.ReportViewer();
            this.ViewERCTableAdapter = new BroadcasterReporting.OnAirDataSetTableAdapters.ViewERCTableAdapter();
            ((System.ComponentModel.ISupportInitialize)(this.ViewERCBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.OnAirDataSet)).BeginInit();
            this.SuspendLayout();
            // 
            // ViewERCBindingSource
            // 
            this.ViewERCBindingSource.DataMember = "ViewERC";
            this.ViewERCBindingSource.DataSource = this.OnAirDataSet;
            // 
            // OnAirDataSet
            // 
            this.OnAirDataSet.DataSetName = "OnAirDataSet";
            this.OnAirDataSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // reportViewer1
            // 
            this.reportViewer1.Dock = System.Windows.Forms.DockStyle.Fill;
            reportDataSource1.Name = "OnAirDataSet_ViewERC";
            reportDataSource1.Value = this.ViewERCBindingSource;
            this.reportViewer1.LocalReport.DataSources.Add(reportDataSource1);
            this.reportViewer1.LocalReport.ReportEmbeddedResource = "BroadcasterReporting.Report1.rdlc";
            this.reportViewer1.Location = new System.Drawing.Point(0, 0);
            this.reportViewer1.Name = "reportViewer1";
            this.reportViewer1.Size = new System.Drawing.Size(682, 386);
            this.reportViewer1.TabIndex = 0;
            this.reportViewer1.Load += new System.EventHandler(this.reportViewer1_Load);
            // 
            // ViewERCTableAdapter
            // 
            this.ViewERCTableAdapter.ClearBeforeFill = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(682, 386);
            this.Controls.Add(this.reportViewer1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.ViewERCBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.OnAirDataSet)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private Microsoft.Reporting.WinForms.ReportViewer reportViewer1;
        private System.Windows.Forms.BindingSource ViewERCBindingSource;
        private OnAirDataSet OnAirDataSet;
        private BroadcasterReporting.OnAirDataSetTableAdapters.ViewERCTableAdapter ViewERCTableAdapter;
    }
}

