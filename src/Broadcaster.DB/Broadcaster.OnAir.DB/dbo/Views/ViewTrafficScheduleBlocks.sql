CREATE VIEW [dbo].[ViewTrafficScheduleBlocks]
AS
SELECT     Broadcaster.dbo.TrafficScheduleBlocks.BlockID, Broadcaster.dbo.TrafficScheduleBlocks.Sun, Broadcaster.dbo.TrafficScheduleBlocks.Mon, 
                      Broadcaster.dbo.TrafficScheduleBlocks.Tue, Broadcaster.dbo.TrafficScheduleBlocks.Wed, Broadcaster.dbo.TrafficScheduleBlocks.Thu, 
                      Broadcaster.dbo.TrafficScheduleBlocks.Fri, Broadcaster.dbo.TrafficScheduleBlocks.Sat, Broadcaster.dbo.TrafficScheduleBlocks.[Position], 
                      Broadcaster.dbo.TrafficScheduleBlocks.[Value], Broadcaster.dbo.TrafficScheduleBlocks.ScheduleID, Broadcaster.dbo.TrafficScheduleBlocks.StationID, 
                      Broadcaster.dbo.TrafficScheduleBlocks.StartingDate, Broadcaster.dbo.TrafficScheduleBlocks.EndingDate, dbo.BlocksDefinition.Name AS Name, 
                      dbo.BlocksDefinition.[Time] AS Time
FROM         Broadcaster.dbo.TrafficScheduleBlocks INNER JOIN
                      dbo.BlocksDefinition ON Broadcaster.dbo.TrafficScheduleBlocks.BlockID = dbo.BlocksDefinition.ID
