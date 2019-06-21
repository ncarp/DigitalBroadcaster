CREATE TABLE [dbo].[OnAirAnomaliesLog] (
    [ID]      INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Date]    DATETIME         NULL,
    [Action]  CHAR (20)        NULL,
    [Info]    TEXT             NULL,
    [rowguid] UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_OnAirAnomaliesLog] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

