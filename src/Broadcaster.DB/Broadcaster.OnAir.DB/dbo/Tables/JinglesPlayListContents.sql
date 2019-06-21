CREATE TABLE [dbo].[JinglesPlayListContents] (
    [ID]        INT      NOT NULL,
    [JingleID]  INT      NOT NULL,
    [StartDate] DATETIME CONSTRAINT [DF_JinglesPlayListContents_StartDate] DEFAULT (getdate()) NULL,
    [EndDate]   DATETIME CONSTRAINT [DF_JinglesPlayListContents_EndDate] DEFAULT (((2500)-(1))-(1)) NULL,
    CONSTRAINT [PK_JinglesPlayListContents] PRIMARY KEY CLUSTERED ([ID] ASC, [JingleID] ASC) WITH (FILLFACTOR = 90)
);

