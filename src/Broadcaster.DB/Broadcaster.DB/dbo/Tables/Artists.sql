CREATE TABLE [dbo].[Artists] (
    [ID]            INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]          CHAR (100)       NULL,
    [Adress]        CHAR (255)       NULL,
    [www]           CHAR (255)       NULL,
    [Activ]         INT              CONSTRAINT [DF_Artists_Activ] DEFAULT ((1)) NULL,
    [NationalityID] INT              NULL,
    [Obs]           TEXT             NULL,
    [eMail]         CHAR (255)       NULL,
    [Photo]         IMAGE            NULL,
    [DRM35]         CHAR (10)        NULL,
    [FanClub]       TEXT             NULL,
    [Birthdate]     DATETIME         NULL,
    [RecordLabelID] INT              NULL,
    [rowguid]       UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Artists] PRIMARY KEY NONCLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_2099048]
    ON [dbo].[Artists]([rowguid] ASC) WITH (FILLFACTOR = 90);

