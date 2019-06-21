CREATE TABLE [dbo].[Languages] (
    [ID]      INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]    CHAR (50)        NULL,
    [Activ]   INT              NULL,
    [DRM35]   CHAR (10)        NULL,
    [rowguid] UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Languages] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_322100188]
    ON [dbo].[Languages]([rowguid] ASC) WITH (FILLFACTOR = 90);

