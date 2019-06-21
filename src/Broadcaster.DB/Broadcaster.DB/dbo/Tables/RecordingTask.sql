CREATE TABLE [dbo].[RecordingTask] (
    [ID]        INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]      CHAR (100)       NULL,
    [TalentID]  INT              NOT NULL,
    [Deadline]  DATETIME         NULL,
    [Todo]      TEXT             NULL,
    [Completed] INT              CONSTRAINT [DF_RecordingTask_Completed] DEFAULT ((0)) NULL,
    [rowguid]   UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_RecordingTask] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1122103038]
    ON [dbo].[RecordingTask]([rowguid] ASC) WITH (FILLFACTOR = 90);

