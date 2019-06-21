CREATE TABLE [dbo].[MusicTracks] (
    [ID]            INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [ArtistID]      INT              NULL,
    [Title]         CHAR (100)       NULL,
    [Lyrics]        CHAR (100)       NULL,
    [Music]         CHAR (100)       NULL,
    [Producer]      CHAR (100)       NULL,
    [Musicians]     TEXT             NULL,
    [Studio]        CHAR (100)       NULL,
    [Tecnicians]    TEXT             NULL,
    [RecordID]      INT              NULL,
    [RecordLabelID] INT              NULL,
    [LanguageID]    INT              NULL,
    [CategoryID]    INT              NULL,
    [Rythm]         INT              NULL,
    [Date]          DATETIME         NULL,
    [Obs]           TEXT             NULL,
    [Available]     INT              CONSTRAINT [DF_MusicTracks_Available] DEFAULT ((1)) NULL,
    [Activ]         INT              CONSTRAINT [DF_MusicTracks_Activ] DEFAULT ((1)) NULL,
    [Storage]       CHAR (50)        NULL,
    [PathID]        INT              NULL,
    [Start]         INT              NULL,
    [FadeIn]        INT              NULL,
    [Intro]         INT              NULL,
    [FadeOut]       INT              NULL,
    [Mix]           INT              NULL,
    [Finish]        INT              NULL,
    [LoopA]         INT              CONSTRAINT [DF_MusicTracks_LoopA] DEFAULT ((0)) NULL,
    [LoopB]         INT              CONSTRAINT [DF_MusicTracks_LoopB] DEFAULT ((0)) NULL,
    [FileType]      CHAR (10)        CONSTRAINT [DF_MusicTracks_FileType] DEFAULT ('.wav') NULL,
    [rowguid]       UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    [Track]         INT              CONSTRAINT [DF_MusicTracks_Track] DEFAULT ((0)) NOT NULL,
    [InsertDate]    DATETIME         CONSTRAINT [DF_MusicTracks_InsertDate] DEFAULT (getdate()) NULL,
    CONSTRAINT [PK_MusicTracks] PRIMARY KEY NONCLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE NONCLUSTERED INDEX [ArtistID]
    ON [dbo].[MusicTracks]([ArtistID] ASC) WITH (FILLFACTOR = 90);


GO
CREATE NONCLUSTERED INDEX [Category]
    ON [dbo].[MusicTracks]([CategoryID] ASC) WITH (FILLFACTOR = 90);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_658101385]
    ON [dbo].[MusicTracks]([rowguid] ASC) WITH (FILLFACTOR = 90);


GO
CREATE NONCLUSTERED INDEX [Language]
    ON [dbo].[MusicTracks]([LanguageID] ASC) WITH (FILLFACTOR = 90);

