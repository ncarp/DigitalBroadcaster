CREATE TABLE [dbo].[VoiceInserts] (
    [ID]       INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]     CHAR (100)       NULL,
    [FileName] CHAR (255)       NULL,
    [Path]     INT              NULL,
    [Start]    INT              NULL,
    [Finish]   INT              NULL,
    [TalentID] INT              NULL,
    [Activ]    INT              NULL,
    [rowguid]  UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_VoiceInserts] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

