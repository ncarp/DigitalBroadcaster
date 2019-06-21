CREATE TABLE [dbo].[OnAirUser] (
    [ID]            INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [Name]          CHAR (100)       NOT NULL,
    [Password]      CHAR (10)        NULL,
    [StationAccess] CHAR (100)       NULL,
    [Activ]         INT              CONSTRAINT [DF_OnAirUser_Activ] DEFAULT ((1)) NULL,
    [SoundRecorder] INT              CONSTRAINT [DF_OnAirUser_SoundRecorder] DEFAULT ((0)) NULL,
    [Scheduler]     INT              CONSTRAINT [DF_OnAirUser_Scheduler] DEFAULT ((0)) NULL,
    [MusicEditing]  INT              CONSTRAINT [DF_OnAirUser_MusicEditing] DEFAULT ((0)) NULL,
    [Blocks]        INT              CONSTRAINT [DF_OnAirUser_Blocks] DEFAULT ((0)) NULL,
    [rowguid]       UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_OnAirUser] PRIMARY KEY CLUSTERED ([ID] ASC) WITH (FILLFACTOR = 90)
);


GO
CREATE UNIQUE NONCLUSTERED INDEX [index_978102525]
    ON [dbo].[OnAirUser]([rowguid] ASC) WITH (FILLFACTOR = 90);

