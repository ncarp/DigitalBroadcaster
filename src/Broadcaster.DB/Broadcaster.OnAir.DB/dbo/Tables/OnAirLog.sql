CREATE TABLE [dbo].[OnAirLog] (
    [Date]       DATETIME         NULL,
    [ComputerID] INT              NULL,
    [UserID]     INT              NULL,
    [ItemType]   INT              NULL,
    [ItemID]     INT              NULL,
    [keyID]      INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [rowguid]    UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_OnAirLog] PRIMARY KEY CLUSTERED ([keyID] ASC) WITH (FILLFACTOR = 90)
);

