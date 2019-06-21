CREATE TABLE [dbo].[Agency] (
    [ID]          INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]        CHAR (100)       NOT NULL,
    [Adress]      CHAR (255)       NULL,
    [ZIP]         CHAR (100)       NULL,
    [Telephone]   CHAR (100)       NULL,
    [Fax]         CHAR (100)       NULL,
    [eMail]       CHAR (100)       NULL,
    [WWW]         CHAR (100)       NULL,
    [Contact]     CHAR (100)       NULL,
    [FID]         CHAR (12)        NULL,
    [Salesperson] INT              NULL,
    [OBS]         TEXT             NULL,
    [Activ]       INT              CONSTRAINT [DF_Agency_Activ] DEFAULT ((1)) NULL,
    [rowguid]     UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Agency] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_2101582525]
    ON [dbo].[Agency]([rowguid] ASC) WITH (FILLFACTOR = 90);

