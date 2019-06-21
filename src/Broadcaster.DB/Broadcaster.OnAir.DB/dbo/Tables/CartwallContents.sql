CREATE TABLE [dbo].[CartwallContents] (
    [CartwallID] INT              NULL,
    [Position]   INT              NULL,
    [Type]       INT              CONSTRAINT [DF_CartwallContents_Type] DEFAULT ((0)) NULL,
    [ElementID]  INT              CONSTRAINT [DF_CartwallContents_ElementID] DEFAULT ((0)) NULL,
    [AutoFade]   INT              CONSTRAINT [DF_CartwallContents_AutoFade] DEFAULT ((0)) NULL,
    [Loop]       INT              CONSTRAINT [DF_CartwallContents_Loop] DEFAULT ((0)) NULL,
    [keyID]      INT              IDENTITY (1, 1) NOT FOR REPLICATION NOT NULL,
    [rowguid]    UNIQUEIDENTIFIER DEFAULT (newid()) ROWGUIDCOL NOT NULL,
    CONSTRAINT [PK_CartwallContents] PRIMARY KEY CLUSTERED ([keyID] ASC) WITH (FILLFACTOR = 90)
);

