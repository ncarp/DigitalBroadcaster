CREATE TABLE [dbo].[RadioStations] (
    [ID]      INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]    CHAR (100)       NULL,
    [Adress]  TEXT             NULL,
    [LogoURL] CHAR (100)       NULL,
    [DSN]     CHAR (100)       NULL,
    [DB]      CHAR (100)       NULL,
    [rowguid] UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_RadioStations] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1090102924]
    ON [dbo].[RadioStations]([rowguid] ASC) WITH (FILLFACTOR = 90);

