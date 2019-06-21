CREATE TABLE [dbo].[RmsOnAir] (
    [RMID]         INT              NULL,
    [StartingDate] DATETIME         NULL,
    [EndingDate]   DATETIME         NULL,
    [ID]           INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [rowguid]      UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_RmsOnAir] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

