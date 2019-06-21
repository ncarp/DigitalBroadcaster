CREATE TABLE [dbo].[PlayLists-Contents] (
    [ListID]       INT              NOT NULL,
    [MusicTrackID] INT              NOT NULL,
    [ID]           INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [rowguid]      UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_PlayLists-Contents] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

