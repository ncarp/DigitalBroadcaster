CREATE TABLE [dbo].[JinglesOnAir] (
    [JingleID]     INT              NOT NULL,
    [StartingDate] DATETIME         CONSTRAINT [DF_JinglesOnAir_StartingDate] DEFAULT (((1990)-(1))-(1)) NULL,
    [EndingDate]   DATETIME         CONSTRAINT [DF_JinglesOnAir_EndingDate] DEFAULT (((2500)-(12))-(31)) NULL,
    [keyID]        INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [rowguid]      UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_JinglesOnAir] PRIMARY KEY CLUSTERED ([keyID] ASC) WITH (FILLFACTOR = 90)
);

