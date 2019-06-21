CREATE TABLE [dbo].[RMs] (
    [ID]        INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]      CHAR (100)       NULL,
    [TypeID]    INT              NULL,
    [KeyWords]  CHAR (100)       NULL,
    [Obs]       TEXT             NULL,
    [Activ]     INT              CONSTRAINT [DF_RMs_Activ] DEFAULT ((1)) NULL,
    [Date]      DATETIME         NULL,
    [PathID]    INT              NULL,
    [FileName]  CHAR (255)       NULL,
    [Start]     INT              NULL,
    [Mix]       INT              NULL,
    [Finish]    INT              NULL,
    [DRM35]     CHAR (20)        NULL,
    [ArchiveID] INT              CONSTRAINT [DF_RMs_ArchiveID] DEFAULT ((0)) NULL,
    [rowguid]   UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_RMs] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1298103665]
    ON [dbo].[RMs]([rowguid] ASC) WITH (FILLFACTOR = 90);

