CREATE TABLE [dbo].[RecordingVersion] (
    [ID]          INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [RecordingID] INT              NULL,
    [Name]        CHAR (100)       NULL,
    [FileName]    CHAR (255)       NULL,
    [PathID]      INT              NULL,
    [Remarks]     TEXT             NULL,
    [Deleted]     INT              CONSTRAINT [DF_RecordingVersion_Deleted] DEFAULT ((0)) NULL,
    [rowguid]     UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_RecordingVersion] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1170103209]
    ON [dbo].[RecordingVersion]([rowguid] ASC) WITH (FILLFACTOR = 90);

