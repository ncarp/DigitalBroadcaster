CREATE TABLE [dbo].[TrafficScheduleDefinition] (
    [ID]           INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [StartingDate] DATETIME         NULL,
    [EndingDate]   DATETIME         NULL,
    [Insertions]   INT              NULL,
    [Value]        MONEY            NULL,
    [Type]         INT              NULL,
    [TypeOfValue]  INT              CONSTRAINT [DF_TrafficScheduleDefinition_TypeOfValue] DEFAULT ((0)) NULL,
    [Suspend]      INT              CONSTRAINT [DF_TrafficScheduleDefinition_Suspend] DEFAULT ((0)) NULL,
    [DRM35]        CHAR (20)        NULL,
    [StationID]    INT              NULL,
    [CustomerID]   INT              NULL,
    [rowguid]      UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_TrafficScheduleDefinition] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1554104577]
    ON [dbo].[TrafficScheduleDefinition]([rowguid] ASC) WITH (FILLFACTOR = 90);

