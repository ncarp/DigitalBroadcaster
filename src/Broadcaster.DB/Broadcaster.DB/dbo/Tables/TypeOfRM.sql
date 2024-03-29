﻿CREATE TABLE [dbo].[TypeOfRM] (
    [ID]      INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]    CHAR (100)       NULL,
    [Activ]   INT              CONSTRAINT [DF_TypeOfRM_Activ] DEFAULT ((1)) NULL,
    [rowguid] UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_TypeOfRM] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1730105204]
    ON [dbo].[TypeOfRM]([rowguid] ASC) WITH (FILLFACTOR = 90);

