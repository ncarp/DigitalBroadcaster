CREATE TABLE [dbo].[Traffic] (
    [ID]         INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [BlockID]    INT              CONSTRAINT [DF_Traffic_BlockID] DEFAULT ((0)) NULL,
    [BlockDate]  DATETIME         CONSTRAINT [DF_Traffic_BlockDate] DEFAULT (NULL) NULL,
    [ScheduleID] INT              CONSTRAINT [DF_Traffic_ScheduleID] DEFAULT ((0)) NULL,
    [Value]      FLOAT (53)       CONSTRAINT [DF_Traffic_Value] DEFAULT ((0)) NULL,
    [Aired]      INT              CONSTRAINT [DF_Traffic_Aired] DEFAULT ((0)) NULL,
    [AiringDate] DATETIME         NULL,
    [TalentID]   INT              NULL,
    [Suspend]    INT              CONSTRAINT [DF_Traffic_Suspend] DEFAULT ((0)) NULL,
    [Position]   INT              CONSTRAINT [DF_Traffic_Position] DEFAULT ((0)) NULL,
    [SpotID]     INT              NOT NULL,
    [rowguid]    UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Traffic] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

