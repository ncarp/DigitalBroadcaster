CREATE TABLE [dbo].[Salesperson] (
    [ID]        INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]      CHAR (100)       NULL,
    [Adress]    TEXT             NULL,
    [ZIP]       CHAR (100)       NULL,
    [NC]        CHAR (12)        NULL,
    [Phone]     CHAR (50)        NULL,
    [Fax]       CHAR (50)        NULL,
    [eMail]     CHAR (50)        NULL,
    [Comission] FLOAT (53)       NULL,
    [Remarks]   TEXT             NULL,
    [Activ]     INT              CONSTRAINT [DF_Vendedores_Activ] DEFAULT ((1)) NULL,
    [DRM35]     CHAR (20)        NULL,
    [rowguid]   UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Salesperson] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1362103893]
    ON [dbo].[Salesperson]([rowguid] ASC) WITH (FILLFACTOR = 90);

