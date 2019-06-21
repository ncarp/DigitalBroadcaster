CREATE TABLE [dbo].[Instrumentals] (
    [ID]        INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [TypeID]    INT              NULL,
    [ElementID] INT              NULL,
    [LastDate]  DATETIME         NULL,
    [rowguid]   UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Instrumentals] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

