CREATE TABLE [dbo].[Scheduling] (
    [ID]           INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Date]         DATETIME         NULL,
    [ItemOrder]    INT              NULL,
    [ItemType]     INT              NULL,
    [ItemID]       INT              NULL,
    [ItemParentID] INT              CONSTRAINT [DF_Scheduling_ItemParentID] DEFAULT ((0)) NULL,
    [ScheduleID]   INT              NULL,
    [Start]        INT              CONSTRAINT [DF_Scheduling_Start] DEFAULT ((0)) NULL,
    [Mix]          INT              CONSTRAINT [DF_Scheduling_Mix] DEFAULT ((0)) NULL,
    [End]          INT              CONSTRAINT [DF_Scheduling_End] DEFAULT ((0)) NULL,
    [Priority]     INT              CONSTRAINT [DF_Scheduling_Priority] DEFAULT ((0)) NULL,
    [Aired]        INT              CONSTRAINT [DF_Scheduling_Aired] DEFAULT ((0)) NULL,
    [TemplateID]   INT              CONSTRAINT [DF_Scheduling_TemplateID] DEFAULT ((0)) NULL,
    [rowguid]      UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Scheduling] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

