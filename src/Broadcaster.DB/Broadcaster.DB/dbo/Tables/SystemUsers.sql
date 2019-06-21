CREATE TABLE [dbo].[SystemUsers] (
    [Id]         INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]       CHAR (100)       NULL,
    [Permission] BINARY (100)     NULL,
    [rowguid]    UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_SystemUsers] PRIMARY KEY CLUSTERED ([Id] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1474104292]
    ON [dbo].[SystemUsers]([rowguid] ASC) WITH (FILLFACTOR = 90);

