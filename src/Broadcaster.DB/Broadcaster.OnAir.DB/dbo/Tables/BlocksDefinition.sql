CREATE TABLE [dbo].[BlocksDefinition] (
    [ID]            INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]          CHAR (100)       NULL,
    [Sun]           INT              NULL,
    [Mon]           INT              NULL,
    [Tue]           INT              NULL,
    [Wed]           INT              NULL,
    [Thu]           INT              NULL,
    [Fri]           INT              NULL,
    [Sat]           INT              NULL,
    [Time]          INT              NULL,
    [InsertionType] INT              NULL,
    [Sponsor]       INT              NULL,
    [Activ]         INT              NULL,
    [DRM]           CHAR (5)         NULL,
    [rowguid]       UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_BlocksDefinition] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

