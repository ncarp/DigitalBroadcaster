CREATE TABLE [dbo].[TrafficScheduleBlocks] (
    [BlockID]      INT              NULL,
    [Sun]          INT              NULL,
    [Mon]          INT              NULL,
    [Tue]          INT              NULL,
    [Wed]          INT              NULL,
    [Thu]          INT              NULL,
    [Fri]          INT              NULL,
    [Sat]          INT              NULL,
    [Position]     INT              NULL,
    [Value]        MONEY            NULL,
    [ScheduleID]   INT              NULL,
    [StationID]    INT              NULL,
    [StartingDate] DATETIME         NULL,
    [EndingDate]   DATETIME         NULL,
    [keyID]        INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [rowguid]      UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_TrafficScheduleBlocks] PRIMARY KEY CLUSTERED ([keyID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_229575856]
    ON [dbo].[TrafficScheduleBlocks]([rowguid] ASC) WITH (FILLFACTOR = 90);

