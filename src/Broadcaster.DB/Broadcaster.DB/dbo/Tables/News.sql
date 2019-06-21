CREATE TABLE [dbo].[News] (
    [ID]       INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]     CHAR (100)       NULL,
    [TypeID]   INT              NULL,
    [Date]     DATETIME         NULL,
    [Activ]    INT              CONSTRAINT [DF_News_Activ] DEFAULT ((1)) NULL,
    [NewsText] TEXT             NULL,
    [KeyWords] CHAR (100)       NULL,
    [rowguid]  UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_News] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_930102354]
    ON [dbo].[News]([rowguid] ASC) WITH (FILLFACTOR = 90);

