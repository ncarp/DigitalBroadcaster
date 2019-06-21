CREATE TABLE [dbo].[Fillers] (
    [ID]      INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [TypeID]  INT              NULL,
    [ItemID]  INT              NULL,
    [rowguid] UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Fillers] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

