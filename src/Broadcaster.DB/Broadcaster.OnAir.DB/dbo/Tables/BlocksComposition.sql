CREATE TABLE [dbo].[BlocksComposition] (
    [ID]           INT              NOT NULL,
    [Position]     INT              NULL,
    [ItemType]     INT              NULL,
    [ItemID]       INT              CONSTRAINT [DF_BlocksComposition_ItemID] DEFAULT ((0)) NULL,
    [StartingDate] DATETIME         CONSTRAINT [DF_BlocksComposition_StartingDate] DEFAULT ('2000-01-01') NULL,
    [EndingDate]   DATETIME         CONSTRAINT [DF_BlocksComposition_EndingDate] DEFAULT ('2500-12-31') NULL,
    [Sun]          INT              CONSTRAINT [DF_BlocksComposition_Sun] DEFAULT ((1)) NULL,
    [Mon]          INT              CONSTRAINT [DF_BlocksComposition_Mon] DEFAULT ((1)) NULL,
    [Tue]          INT              CONSTRAINT [DF_BlocksComposition_Tue] DEFAULT ((1)) NULL,
    [Wed]          INT              CONSTRAINT [DF_BlocksComposition_Wed] DEFAULT ((1)) NULL,
    [Thu]          INT              CONSTRAINT [DF_BlocksComposition_Thu] DEFAULT ((1)) NULL,
    [Fri]          INT              CONSTRAINT [DF_BlocksComposition_Fri] DEFAULT ((1)) NULL,
    [Sat]          INT              CONSTRAINT [DF_BlocksComposition_Sat] DEFAULT ((1)) NULL,
    [keyID]        INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [rowguid]      UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_BlocksComposition] PRIMARY KEY CLUSTERED ([keyID] ASC) WITH (FILLFACTOR = 90)
);

