CREATE TABLE [dbo].[Log] (
    [Date]       DATETIME         CONSTRAINT [DF_Log_LogData] DEFAULT (getdate()) NOT NULL,
    [ComputerID] INT              NOT NULL,
    [UserID]     INT              NULL,
    [ActionID]   INT              NULL,
    [TypeID]     INT              NULL,
    [ItemID]     INT              NULL,
    [lRadioID]   INT              CONSTRAINT [DF_Log_lRadioID] DEFAULT ((0)) NULL,
    [XTRA]       INT              CONSTRAINT [DF_Log_XTRA] DEFAULT ((0)) NULL,
    [ID]         INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [rowguid]    UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_Log] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_546100986]
    ON [dbo].[Log]([rowguid] ASC) WITH (FILLFACTOR = 90);

