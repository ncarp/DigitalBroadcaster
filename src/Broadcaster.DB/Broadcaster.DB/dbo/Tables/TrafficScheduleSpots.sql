CREATE TABLE [dbo].[TrafficScheduleSpots] (
    [ScheduleID]   INT              NULL,
    [Position]     INT              NULL,
    [SpotID]       INT              NULL,
    [StartingDate] DATETIME         NULL,
    [EndingDate]   DATETIME         NULL,
    [Sun]          INT              NULL,
    [Mon]          INT              NULL,
    [Tue]          INT              NULL,
    [Wed]          INT              NULL,
    [Thu]          INT              NULL,
    [Fri]          INT              NULL,
    [Sat]          INT              NULL,
    [keyID]        INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [rowguid]      UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_TrafficScheduleSpots] PRIMARY KEY CLUSTERED ([keyID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_261575970]
    ON [dbo].[TrafficScheduleSpots]([rowguid] ASC) WITH (FILLFACTOR = 90);

