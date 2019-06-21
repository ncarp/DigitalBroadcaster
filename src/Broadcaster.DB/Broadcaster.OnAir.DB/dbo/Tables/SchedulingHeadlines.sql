CREATE TABLE [dbo].[SchedulingHeadlines] (
    [ID]         INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Date]       DATETIME         NULL,
    [EndingDate] DATETIME         NULL,
    [Priority]   INT              NULL,
    [Name]       CHAR (100)       NULL,
    [TemplateID] INT              NULL,
    [rowguid]    UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_SchedulingHeadlines] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

