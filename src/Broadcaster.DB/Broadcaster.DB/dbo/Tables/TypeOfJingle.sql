CREATE TABLE [dbo].[TypeOfJingle] (
    [ID]      INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]    CHAR (100)       NULL,
    [Activ]   INT              CONSTRAINT [DF_TypeOfJingle_Activ] DEFAULT ((1)) NULL,
    [DRM35]   CHAR (10)        NULL,
    [rowguid] UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_TypeOfJingle] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1682105033]
    ON [dbo].[TypeOfJingle]([rowguid] ASC) WITH (FILLFACTOR = 90);

