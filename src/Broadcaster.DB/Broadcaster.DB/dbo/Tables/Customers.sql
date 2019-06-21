CREATE TABLE [dbo].[Customers] (
    [ID]             INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]           CHAR (100)       NOT NULL,
    [Adress]         CHAR (255)       NULL,
    [ZIP]            CHAR (100)       NULL,
    [Phone]          CHAR (100)       NULL,
    [Fax]            CHAR (100)       NULL,
    [eMail]          CHAR (100)       NULL,
    [www]            CHAR (100)       NULL,
    [Contact]        CHAR (100)       NULL,
    [nc]             CHAR (20)        NULL,
    [AgencyID]       INT              NULL,
    [BusinessTypeID] INT              NULL,
    [SalespersonID]  INT              NULL,
    [Obs]            TEXT             NULL,
    [Activ]          INT              CONSTRAINT [DF_Customers_Activ] DEFAULT ((1)) NULL,
    [Cli35]          CHAR (11)        NULL,
    [rowguid]        UNIQUEIDENTIFIER CONSTRAINT [DF__Customers__rowgu__4460231C] DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    [NC2]            CHAR (100)       NULL,
    [Name2]          CHAR (100)       NULL,
    [Number]         CHAR (20)        NULL,
    [CelPhone]       CHAR (100)       NULL,
    CONSTRAINT [PK_Customers] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [ID]
    ON [dbo].[Customers]([ID] ASC) WITH (FILLFACTOR = 90);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_114099447]
    ON [dbo].[Customers]([rowguid] ASC) WITH (FILLFACTOR = 90);

