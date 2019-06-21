CREATE TABLE [dbo].[Jingles] (
    [ID]       INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [TypeID]   INT              NULL,
    [Name]     CHAR (100)       NULL,
    [Rythm]    INT              CONSTRAINT [DF_Jingles_Rythm] DEFAULT ((50)) NULL,
    [LoopA]    INT              CONSTRAINT [DF_Jingles_LoopA] DEFAULT ((0)) NULL,
    [LoopB]    INT              CONSTRAINT [DF_Jingles_LoopB] DEFAULT ((0)) NULL,
    [Start]    INT              NULL,
    [Intro]    INT              NULL,
    [Mix]      INT              NULL,
    [Finish]   INT              NULL,
    [Activ]    INT              CONSTRAINT [DF_Jingles_Activ] DEFAULT ((1)) NULL,
    [Ready]    INT              CONSTRAINT [DF_Jingles_Ready] DEFAULT ((1)) NULL,
    [PathID]   INT              NULL,
    [FileName] CHAR (255)       NULL,
    [DRM35]    CHAR (6)         NULL,
    [rowguid]  UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Jingles] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_210099789]
    ON [dbo].[Jingles]([rowguid] ASC) WITH (FILLFACTOR = 90);

