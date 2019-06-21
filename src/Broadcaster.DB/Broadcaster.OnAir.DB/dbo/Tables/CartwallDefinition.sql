CREATE TABLE [dbo].[CartwallDefinition] (
    [ID]      INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]    CHAR (100)       NULL,
    [UserID]  INT              NULL,
    [Info]    INT              CONSTRAINT [DF_CartwallDefinition_Info] DEFAULT ((0)) NULL,
    [rowguid] UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_CartwallDefinition] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

