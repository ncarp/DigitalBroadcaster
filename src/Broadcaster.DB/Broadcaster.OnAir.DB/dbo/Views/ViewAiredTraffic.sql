CREATE VIEW [dbo].[ViewAiredTraffic]
AS
SELECT     dbo.Traffic.AiringDate, dbo.Traffic.SpotID, Broadcaster.dbo.Spots.Name AS SpotName, Broadcaster.dbo.Customers.Name AS CustomerName, 
                      Broadcaster.dbo.Spots.CustomerID, dbo.Traffic.Value, dbo.BlocksDefinition.Name AS BlockName, 
                      Broadcaster.dbo.TrafficScheduleDefinition.DRM35 AS PI
FROM         dbo.Traffic INNER JOIN
                      Broadcaster.dbo.Spots ON dbo.Traffic.SpotID = Broadcaster.dbo.Spots.ID INNER JOIN
                      Broadcaster.dbo.Customers ON Broadcaster.dbo.Spots.CustomerID = Broadcaster.dbo.Customers.ID LEFT OUTER JOIN
                      Broadcaster.dbo.TrafficScheduleDefinition ON dbo.Traffic.ScheduleID = Broadcaster.dbo.TrafficScheduleDefinition.ID LEFT OUTER JOIN
                      dbo.BlocksDefinition ON dbo.Traffic.BlockID = dbo.BlocksDefinition.ID
WHERE     (dbo.Traffic.Aired = 1)

GO
EXECUTE sp_addextendedproperty @name = N'MS_DiagramPane2', @value = N'in ColumnWidths = 11
         Column = 1440
         Alias = 900
         Table = 1170
         Output = 720
         Append = 1400
         NewValue = 1170
         SortType = 1350
         SortOrder = 1410
         GroupBy = 1350
         Filter = 1350
         Or = 1350
         Or = 1350
         Or = 1350
      End
   End
End
', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'VIEW', @level1name = N'ViewAiredTraffic';


GO
EXECUTE sp_addextendedproperty @name = N'MS_DiagramPaneCount', @value = 2, @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'VIEW', @level1name = N'ViewAiredTraffic';

