CREATE TABLE [dbo].[Players] (
    [Order]      INT        NOT NULL,
    [ItemType]   INT        NULL,
    [ItemID]     INT        NULL,
    [ArtistID]   INT        CONSTRAINT [DF_Players_ArtistID] DEFAULT ((0)) NULL,
    [ArtistName] CHAR (250) NULL,
    [TrackTitle] CHAR (250) NULL,
    CONSTRAINT [PK_Players] PRIMARY KEY CLUSTERED ([Order] ASC) WITH (FILLFACTOR = 90)
);

