CREATE TABLE [dbo].[Nationalities] (
    [ID]          INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Nationality] CHAR (50)        NULL,
    [ZoneID]      INT              NULL,
    [Activ]       INT              NULL,
    [rowguid]     UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Nationalities] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_898102240]
    ON [dbo].[Nationalities]([rowguid] ASC) WITH (FILLFACTOR = 90);

