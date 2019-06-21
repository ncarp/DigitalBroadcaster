CREATE TABLE [dbo].[NewsLineUpComponents] (
    [LineUpID] INT              NULL,
    [Position] INT              NULL,
    [NewsID]   INT              NULL,
    [Prev]     INT              NULL,
    [Next]     INT              NULL,
    [keyID]    INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [rowguid]  UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_NewsLineUpComponents] PRIMARY KEY CLUSTERED ([keyID] ASC) WITH (FILLFACTOR = 90)
);

