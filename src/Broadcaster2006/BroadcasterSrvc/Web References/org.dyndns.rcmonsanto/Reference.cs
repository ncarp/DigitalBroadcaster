﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30128.1
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// 
// This source code was auto-generated by Microsoft.VSDesigner, Version 4.0.30128.1.
// 
#pragma warning disable 1591

namespace BroadcasterSrvc.org.dyndns.rcmonsanto {
    using System;
    using System.Web.Services;
    using System.Diagnostics;
    using System.Web.Services.Protocols;
    using System.ComponentModel;
    using System.Xml.Serialization;
    
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "4.0.30128.1")]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Web.Services.WebServiceBindingAttribute(Name="BroadacasterService1Soap", Namespace="http://high-precision.pt/")]
    public partial class BroadacasterService1 : System.Web.Services.Protocols.SoapHttpClientProtocol {
        
        private System.Threading.SendOrPostCallback HelloOperationCompleted;
        
        private System.Threading.SendOrPostCallback GetPlayersOperationCompleted;
        
        private System.Threading.SendOrPostCallback GetDayScheduleOperationCompleted;
        
        private bool useDefaultCredentialsSetExplicitly;
        
        /// <remarks/>
        public BroadacasterService1() {
            this.Url = global::BroadcasterSrvc.Properties.Settings.Default.BroadcasterSrvc_org_dyndns_rcmonsanto_BroadacasterService1;
            if ((this.IsLocalFileSystemWebService(this.Url) == true)) {
                this.UseDefaultCredentials = true;
                this.useDefaultCredentialsSetExplicitly = false;
            }
            else {
                this.useDefaultCredentialsSetExplicitly = true;
            }
        }
        
        public new string Url {
            get {
                return base.Url;
            }
            set {
                if ((((this.IsLocalFileSystemWebService(base.Url) == true) 
                            && (this.useDefaultCredentialsSetExplicitly == false)) 
                            && (this.IsLocalFileSystemWebService(value) == false))) {
                    base.UseDefaultCredentials = false;
                }
                base.Url = value;
            }
        }
        
        public new bool UseDefaultCredentials {
            get {
                return base.UseDefaultCredentials;
            }
            set {
                base.UseDefaultCredentials = value;
                this.useDefaultCredentialsSetExplicitly = true;
            }
        }
        
        /// <remarks/>
        public event HelloCompletedEventHandler HelloCompleted;
        
        /// <remarks/>
        public event GetPlayersCompletedEventHandler GetPlayersCompleted;
        
        /// <remarks/>
        public event GetDayScheduleCompletedEventHandler GetDayScheduleCompleted;
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://high-precision.pt/Hello", RequestNamespace="http://high-precision.pt/", ResponseNamespace="http://high-precision.pt/", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        public string Hello() {
            object[] results = this.Invoke("Hello", new object[0]);
            return ((string)(results[0]));
        }
        
        /// <remarks/>
        public void HelloAsync() {
            this.HelloAsync(null);
        }
        
        /// <remarks/>
        public void HelloAsync(object userState) {
            if ((this.HelloOperationCompleted == null)) {
                this.HelloOperationCompleted = new System.Threading.SendOrPostCallback(this.OnHelloOperationCompleted);
            }
            this.InvokeAsync("Hello", new object[0], this.HelloOperationCompleted, userState);
        }
        
        private void OnHelloOperationCompleted(object arg) {
            if ((this.HelloCompleted != null)) {
                System.Web.Services.Protocols.InvokeCompletedEventArgs invokeArgs = ((System.Web.Services.Protocols.InvokeCompletedEventArgs)(arg));
                this.HelloCompleted(this, new HelloCompletedEventArgs(invokeArgs.Results, invokeArgs.Error, invokeArgs.Cancelled, invokeArgs.UserState));
            }
        }
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://high-precision.pt/GetPlayers", RequestNamespace="http://high-precision.pt/", ResponseNamespace="http://high-precision.pt/", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        [return: System.Xml.Serialization.XmlArrayItemAttribute(IsNullable=false)]
        public PlayerInfo[] GetPlayers() {
            object[] results = this.Invoke("GetPlayers", new object[0]);
            return ((PlayerInfo[])(results[0]));
        }
        
        /// <remarks/>
        public void GetPlayersAsync() {
            this.GetPlayersAsync(null);
        }
        
        /// <remarks/>
        public void GetPlayersAsync(object userState) {
            if ((this.GetPlayersOperationCompleted == null)) {
                this.GetPlayersOperationCompleted = new System.Threading.SendOrPostCallback(this.OnGetPlayersOperationCompleted);
            }
            this.InvokeAsync("GetPlayers", new object[0], this.GetPlayersOperationCompleted, userState);
        }
        
        private void OnGetPlayersOperationCompleted(object arg) {
            if ((this.GetPlayersCompleted != null)) {
                System.Web.Services.Protocols.InvokeCompletedEventArgs invokeArgs = ((System.Web.Services.Protocols.InvokeCompletedEventArgs)(arg));
                this.GetPlayersCompleted(this, new GetPlayersCompletedEventArgs(invokeArgs.Results, invokeArgs.Error, invokeArgs.Cancelled, invokeArgs.UserState));
            }
        }
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://high-precision.pt/GetDaySchedule", RequestNamespace="http://high-precision.pt/", ResponseNamespace="http://high-precision.pt/", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        [return: System.Xml.Serialization.XmlArrayItemAttribute(IsNullable=false)]
        public ScheduleInfo[] GetDaySchedule(System.DateTime date) {
            object[] results = this.Invoke("GetDaySchedule", new object[] {
                        date});
            return ((ScheduleInfo[])(results[0]));
        }
        
        /// <remarks/>
        public void GetDayScheduleAsync(System.DateTime date) {
            this.GetDayScheduleAsync(date, null);
        }
        
        /// <remarks/>
        public void GetDayScheduleAsync(System.DateTime date, object userState) {
            if ((this.GetDayScheduleOperationCompleted == null)) {
                this.GetDayScheduleOperationCompleted = new System.Threading.SendOrPostCallback(this.OnGetDayScheduleOperationCompleted);
            }
            this.InvokeAsync("GetDaySchedule", new object[] {
                        date}, this.GetDayScheduleOperationCompleted, userState);
        }
        
        private void OnGetDayScheduleOperationCompleted(object arg) {
            if ((this.GetDayScheduleCompleted != null)) {
                System.Web.Services.Protocols.InvokeCompletedEventArgs invokeArgs = ((System.Web.Services.Protocols.InvokeCompletedEventArgs)(arg));
                this.GetDayScheduleCompleted(this, new GetDayScheduleCompletedEventArgs(invokeArgs.Results, invokeArgs.Error, invokeArgs.Cancelled, invokeArgs.UserState));
            }
        }
        
        /// <remarks/>
        public new void CancelAsync(object userState) {
            base.CancelAsync(userState);
        }
        
        private bool IsLocalFileSystemWebService(string url) {
            if (((url == null) 
                        || (url == string.Empty))) {
                return false;
            }
            System.Uri wsUri = new System.Uri(url);
            if (((wsUri.Port >= 1024) 
                        && (string.Compare(wsUri.Host, "localHost", System.StringComparison.OrdinalIgnoreCase) == 0))) {
                return true;
            }
            return false;
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "4.0.30128.1")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace="http://high-precision.pt/")]
    public partial class PlayerInfo {
        
        private int playerNField;
        
        private long itemTypeField;
        
        private long itemIDField;
        
        private long itemParentIDField;
        
        private string itemName1Field;
        
        private string itemName2Field;
        
        /// <remarks/>
        public int PlayerN {
            get {
                return this.playerNField;
            }
            set {
                this.playerNField = value;
            }
        }
        
        /// <remarks/>
        public long ItemType {
            get {
                return this.itemTypeField;
            }
            set {
                this.itemTypeField = value;
            }
        }
        
        /// <remarks/>
        public long ItemID {
            get {
                return this.itemIDField;
            }
            set {
                this.itemIDField = value;
            }
        }
        
        /// <remarks/>
        public long ItemParentID {
            get {
                return this.itemParentIDField;
            }
            set {
                this.itemParentIDField = value;
            }
        }
        
        /// <remarks/>
        public string ItemName1 {
            get {
                return this.itemName1Field;
            }
            set {
                this.itemName1Field = value;
            }
        }
        
        /// <remarks/>
        public string ItemName2 {
            get {
                return this.itemName2Field;
            }
            set {
                this.itemName2Field = value;
            }
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "4.0.30128.1")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace="http://high-precision.pt/")]
    public partial class SongInfo {
        
        private System.DateTime timeField;
        
        private long songIDField;
        
        private string artistNameField;
        
        private string titleField;
        
        /// <remarks/>
        public System.DateTime Time {
            get {
                return this.timeField;
            }
            set {
                this.timeField = value;
            }
        }
        
        /// <remarks/>
        public long SongID {
            get {
                return this.songIDField;
            }
            set {
                this.songIDField = value;
            }
        }
        
        /// <remarks/>
        public string ArtistName {
            get {
                return this.artistNameField;
            }
            set {
                this.artistNameField = value;
            }
        }
        
        /// <remarks/>
        public string Title {
            get {
                return this.titleField;
            }
            set {
                this.titleField = value;
            }
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "4.0.30128.1")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace="http://high-precision.pt/")]
    public partial class ScheduleInfo {
        
        private int scheduleIDField;
        
        private string nameField;
        
        private System.DateTime dateStartField;
        
        private System.DateTime dateFinishField;
        
        private SongInfo[] songsField;
        
        /// <remarks/>
        public int ScheduleID {
            get {
                return this.scheduleIDField;
            }
            set {
                this.scheduleIDField = value;
            }
        }
        
        /// <remarks/>
        public string Name {
            get {
                return this.nameField;
            }
            set {
                this.nameField = value;
            }
        }
        
        /// <remarks/>
        public System.DateTime DateStart {
            get {
                return this.dateStartField;
            }
            set {
                this.dateStartField = value;
            }
        }
        
        /// <remarks/>
        public System.DateTime DateFinish {
            get {
                return this.dateFinishField;
            }
            set {
                this.dateFinishField = value;
            }
        }
        
        /// <remarks/>
        [System.Xml.Serialization.XmlArrayItemAttribute(IsNullable=false)]
        public SongInfo[] Songs {
            get {
                return this.songsField;
            }
            set {
                this.songsField = value;
            }
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "4.0.30128.1")]
    public delegate void HelloCompletedEventHandler(object sender, HelloCompletedEventArgs e);
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "4.0.30128.1")]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    public partial class HelloCompletedEventArgs : System.ComponentModel.AsyncCompletedEventArgs {
        
        private object[] results;
        
        internal HelloCompletedEventArgs(object[] results, System.Exception exception, bool cancelled, object userState) : 
                base(exception, cancelled, userState) {
            this.results = results;
        }
        
        /// <remarks/>
        public string Result {
            get {
                this.RaiseExceptionIfNecessary();
                return ((string)(this.results[0]));
            }
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "4.0.30128.1")]
    public delegate void GetPlayersCompletedEventHandler(object sender, GetPlayersCompletedEventArgs e);
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "4.0.30128.1")]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    public partial class GetPlayersCompletedEventArgs : System.ComponentModel.AsyncCompletedEventArgs {
        
        private object[] results;
        
        internal GetPlayersCompletedEventArgs(object[] results, System.Exception exception, bool cancelled, object userState) : 
                base(exception, cancelled, userState) {
            this.results = results;
        }
        
        /// <remarks/>
        public PlayerInfo[] Result {
            get {
                this.RaiseExceptionIfNecessary();
                return ((PlayerInfo[])(this.results[0]));
            }
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "4.0.30128.1")]
    public delegate void GetDayScheduleCompletedEventHandler(object sender, GetDayScheduleCompletedEventArgs e);
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "4.0.30128.1")]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    public partial class GetDayScheduleCompletedEventArgs : System.ComponentModel.AsyncCompletedEventArgs {
        
        private object[] results;
        
        internal GetDayScheduleCompletedEventArgs(object[] results, System.Exception exception, bool cancelled, object userState) : 
                base(exception, cancelled, userState) {
            this.results = results;
        }
        
        /// <remarks/>
        public ScheduleInfo[] Result {
            get {
                this.RaiseExceptionIfNecessary();
                return ((ScheduleInfo[])(this.results[0]));
            }
        }
    }
}

#pragma warning restore 1591