CREATE TABLE [dbo].[NewsOnAir] (
    [ID]           INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [NewsID]       INT              NULL,
    [StartingDate] DATETIME         NULL,
    [EndingDate]   DATETIME         NULL,
    [rowguid]      UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_NewsOnAir] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

