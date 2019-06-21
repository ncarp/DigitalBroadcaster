CREATE TABLE [dbo].[Sponsors] (
    [SpotID]       INT              NOT NULL,
    [StartingDate] DATETIME         NULL,
    [EndingDate]   DATETIME         NULL,
    [ID]           INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [rowguid]      UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Sponsors] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

