CREATE TABLE [dbo].[ElementType] (
    [ID]      INT              NOT NULL,
    [Name]    CHAR (50)        NULL,
    [rowguid] UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_ElementType] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_2073058421]
    ON [dbo].[ElementType]([rowguid] ASC) WITH (FILLFACTOR = 90);

