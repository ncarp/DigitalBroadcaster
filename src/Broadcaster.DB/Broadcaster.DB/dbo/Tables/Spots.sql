CREATE TABLE [dbo].[Spots] (
    [ID]               INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]             CHAR (100)       NULL,
    [CustomerID]       INT              NULL,
    [AgencyID]         INT              NULL,
    [TypeOfBusinessID] INT              NULL,
    [PathID]           INT              NULL,
    [FileName]         CHAR (255)       NULL,
    [Start]            INT              NULL,
    [Mix]              INT              NULL,
    [Finish]           INT              NULL,
    [Ready]            INT              NULL,
    [Text]             TEXT             NULL,
    [Voices]           TEXT             NULL,
    [Music]            TEXT             NULL,
    [Deadline]         DATETIME         NULL,
    [MainVoiceID]      INT              CONSTRAINT [DF_Spots_MainVoiceID] DEFAULT ((0)) NULL,
    [DRM35]            CHAR (20)        NULL,
    [Obs]              TEXT             NULL,
    [Activ]            INT              CONSTRAINT [DF_Spots_Activ] DEFAULT ((1)) NULL,
    [StandardLength]   INT              NULL,
    [rowguid]          UNIQUEIDENTIFIER CONSTRAINT [DF__Spots__rowguid__68D28DBC] DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Spots] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [ID]
    ON [dbo].[Spots]([ID] ASC) WITH (FILLFACTOR = 90);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1410104064]
    ON [dbo].[Spots]([rowguid] ASC) WITH (FILLFACTOR = 90);

