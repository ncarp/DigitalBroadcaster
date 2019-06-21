CREATE TABLE [dbo].[RecordLabel] (
    [ID]            INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]          CHAR (100)       NULL,
    [Adress]        CHAR (255)       NULL,
    [Activ]         INT              NULL,
    [ParentCompany] INT              NULL,
    [rowguid]       UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_RecordLabel] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1218103380]
    ON [dbo].[RecordLabel]([rowguid] ASC) WITH (FILLFACTOR = 90);

