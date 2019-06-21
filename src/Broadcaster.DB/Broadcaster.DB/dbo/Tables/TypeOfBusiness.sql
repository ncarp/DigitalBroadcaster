CREATE TABLE [dbo].[TypeOfBusiness] (
    [ID]      INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]    CHAR (100)       NULL,
    [Activ]   INT              CONSTRAINT [DF_TypeOfBusiness_Activ] DEFAULT ((1)) NULL,
    [rowguid] UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_TypeOfBusiness] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_1634104862]
    ON [dbo].[TypeOfBusiness]([rowguid] ASC) WITH (FILLFACTOR = 90);

