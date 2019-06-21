CREATE TABLE [dbo].[PlayLists-Def] (
    [ID]      INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]    CHAR (100)       NOT NULL,
    [Activ]   INT              CONSTRAINT [DF_PlayLists-Def_Activ] DEFAULT ((1)) NULL,
    [DRM35]   CHAR (10)        NULL,
    [OnAir]   INT              CONSTRAINT [DF_PlayLists-Def_OnAir] DEFAULT ((1)) NULL,
    [rowguid] UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_PlayLists-Def] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

