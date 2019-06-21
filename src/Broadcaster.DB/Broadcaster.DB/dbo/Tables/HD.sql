CREATE TABLE [dbo].[HD] (
    [ID]         INT        IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Path]       CHAR (255) NULL,
    [Music]      INT        NULL,
    [Jingles]    INT        NULL,
    [Spots]      INT        NULL,
    [RMs]        INT        NULL,
    [TimeSignal] INT        NULL,
    [Takes]      INT        NULL,
    [Producer]   INT        NULL,
    CONSTRAINT [PK_HD] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);

