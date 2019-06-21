CREATE TABLE [dbo].[Voices] (
    [ID]      INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]    CHAR (100)       NULL,
    [Activ]   INT              CONSTRAINT [DF_Vozes_Activ] DEFAULT ((1)) NULL,
    [rowguid] UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Voices] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1778105375]
    ON [dbo].[Voices]([rowguid] ASC) WITH (FILLFACTOR = 90);

