CREATE TABLE [dbo].[Records] (
    [ID]       INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Title]    CHAR (100)       NULL,
    [ArtistID] INT              CONSTRAINT [DF_Records_ArtistID] DEFAULT ((0)) NULL,
    [Date]     DATETIME         NULL,
    [LabelID]  INT              NULL,
    [Producer] CHAR (100)       NULL,
    [Studio]   CHAR (100)       NULL,
    [Remarks]  TEXT             NULL,
    [Cover]    IMAGE            NULL,
    [rowguid]  UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Records] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1250103494]
    ON [dbo].[Records]([rowguid] ASC) WITH (FILLFACTOR = 90);

