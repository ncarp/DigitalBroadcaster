CREATE TABLE [dbo].[SchedulingTemplate] (
    [ID]               INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Type]             INT              NULL,
    [Name]             CHAR (100)       NULL,
    [Category]         INT              CONSTRAINT [DF_SchedulingTemplate_Category] DEFAULT ((0)) NULL,
    [PlayList]         INT              CONSTRAINT [DF_SchedulingTemplate_PlayList] DEFAULT ((0)) NULL,
    [Expression]       INT              CONSTRAINT [DF_SchedulingTemplate_Expression] DEFAULT ((0)) NULL,
    [MinRythm]         INT              CONSTRAINT [DF_SchedulingTemplate_MinRythm] DEFAULT ((0)) NULL,
    [MaxRythm]         INT              CONSTRAINT [DF_SchedulingTemplate_MaxRythm] DEFAULT ((250)) NULL,
    [MinLen]           INT              CONSTRAINT [DF_SchedulingTemplate_MinLen] DEFAULT ((0)) NULL,
    [MaxLen]           INT              CONSTRAINT [DF_SchedulingTemplate_MaxLen] DEFAULT ((900)) NULL,
    [strSQL]           TEXT             NULL,
    [ArtistQuarantine] INT              CONSTRAINT [DF_SchedulingTemplate_ArtistQuarantine] DEFAULT ((2)) NULL,
    [SongQuarantine]   INT              CONSTRAINT [DF_SchedulingTemplate_SongQuarantine] DEFAULT ((2)) NULL,
    [RandomFactor]     INT              CONSTRAINT [DF_SchedulingTemplate_RamdomFactor] DEFAULT ((5)) NULL,
    [LastPos]          INT              CONSTRAINT [DF_SchedulingTemplate_LastPos] DEFAULT ((0)) NULL,
    [rowguid]          UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_SchedulingTemplate] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

