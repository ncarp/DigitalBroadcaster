CREATE TABLE [dbo].[Time] (
    [ID]         INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]       CHAR (100)       NULL,
    [PathID]     INT              NULL,
    [FolderName] CHAR (100)       NULL,
    [rowguid]    UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Time] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1506104406]
    ON [dbo].[Time]([rowguid] ASC) WITH (FILLFACTOR = 90);

