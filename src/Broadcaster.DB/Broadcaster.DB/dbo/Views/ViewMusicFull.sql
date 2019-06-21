CREATE VIEW [dbo].[ViewMusicFull]
AS
SELECT     dbo.MusicTracks.ID, dbo.MusicTracks.ArtistID, dbo.MusicTracks.Title, dbo.MusicTracks.Lyrics, dbo.MusicTracks.Music, dbo.MusicTracks.Producer, 
                      dbo.MusicTracks.Musicians, dbo.MusicTracks.Studio, dbo.MusicTracks.Tecnicians, dbo.MusicTracks.RecordID, dbo.MusicTracks.RecordLabelID, 
                      dbo.MusicTracks.LanguageID, dbo.MusicTracks.CategoryID, dbo.MusicTracks.Rythm, dbo.MusicTracks.Date, dbo.MusicTracks.Obs, 
                      dbo.MusicTracks.Available, dbo.MusicTracks.Activ, dbo.MusicTracks.Storage, dbo.MusicTracks.PathID, dbo.MusicTracks.Start, 
                      dbo.MusicTracks.FadeIn, dbo.MusicTracks.Intro, dbo.MusicTracks.FadeOut, dbo.MusicTracks.Mix, dbo.MusicTracks.Finish, dbo.MusicTracks.LoopA, 
                      dbo.MusicTracks.LoopB, dbo.MusicTracks.FileType, dbo.Artists.Name AS Artist, dbo.Records.Title AS Record, dbo.RecordLabel.Name AS Label, 
                      dbo.Languages.Name AS Expression, dbo.Categories.Name AS Category, dbo.HD.Path, dbo.MusicTracks.InsertDate
FROM         dbo.MusicTracks LEFT OUTER JOIN
                      dbo.Records ON dbo.MusicTracks.RecordID = dbo.Records.ID LEFT OUTER JOIN
                      dbo.Languages ON dbo.MusicTracks.LanguageID = dbo.Languages.ID LEFT OUTER JOIN
                      dbo.Categories ON dbo.MusicTracks.CategoryID = dbo.Categories.ID LEFT OUTER JOIN
                      dbo.Artists ON dbo.MusicTracks.ArtistID = dbo.Artists.ID LEFT OUTER JOIN
                      dbo.RecordLabel ON dbo.MusicTracks.RecordLabelID = dbo.RecordLabel.ID LEFT OUTER JOIN
                      dbo.HD ON dbo.MusicTracks.PathID = dbo.HD.ID



GO
EXECUTE sp_addextendedproperty @name = N'MS_DiagramPane1', @value = N'[0E232FF0-B466-11cf-A24F-00AA00A3EFFF, 1.00]
Begin DesignProperties = 
   Begin PaneConfigurations = 
      Begin PaneConfiguration = 0
         NumPanes = 4
         Configuration = "(H (1[40] 4[20] 2[20] 3) )"
      End
      Begin PaneConfiguration = 1
         NumPanes = 3
         Configuration = "(H (1 [50] 4 [25] 3))"
      End
      Begin PaneConfiguration = 2
         NumPanes = 3
         Configuration = "(H (1 [50] 2 [25] 3))"
      End
      Begin PaneConfiguration = 3
         NumPanes = 3
         Configuration = "(H (4 [30] 2 [40] 3))"
      End
      Begin PaneConfiguration = 4
         NumPanes = 2
         Configuration = "(H (1 [56] 3))"
      End
      Begin PaneConfiguration = 5
         NumPanes = 2
         Configuration = "(H (2 [66] 3))"
      End
      Begin PaneConfiguration = 6
         NumPanes = 2
         Configuration = "(H (4 [50] 3))"
      End
      Begin PaneConfiguration = 7
         NumPanes = 1
         Configuration = "(V (3))"
      End
      Begin PaneConfiguration = 8
         NumPanes = 3
         Configuration = "(H (1[56] 4[18] 2) )"
      End
      Begin PaneConfiguration = 9
         NumPanes = 2
         Configuration = "(H (1 [75] 4))"
      End
      Begin PaneConfiguration = 10
         NumPanes = 2
         Configuration = "(H (1[66] 2) )"
      End
      Begin PaneConfiguration = 11
         NumPanes = 2
         Configuration = "(H (4 [60] 2))"
      End
      Begin PaneConfiguration = 12
         NumPanes = 1
         Configuration = "(H (1) )"
      End
      Begin PaneConfiguration = 13
         NumPanes = 1
         Configuration = "(V (4))"
      End
      Begin PaneConfiguration = 14
         NumPanes = 1
         Configuration = "(V (2))"
      End
      ActivePaneConfig = 0
   End
   Begin DiagramPane = 
      Begin Origin = 
         Top = 0
         Left = 0
      End
      Begin Tables = 
         Begin Table = "MusicTracks"
            Begin Extent = 
               Top = 6
               Left = 38
               Bottom = 114
               Right = 189
            End
            DisplayFlags = 280
            TopColumn = 0
         End
         Begin Table = "Records"
            Begin Extent = 
               Top = 6
               Left = 227
               Bottom = 114
               Right = 378
            End
            DisplayFlags = 280
            TopColumn = 0
         End
         Begin Table = "Languages"
            Begin Extent = 
               Top = 114
               Left = 38
               Bottom = 222
               Right = 189
            End
            DisplayFlags = 280
            TopColumn = 0
         End
         Begin Table = "Categories"
            Begin Extent = 
               Top = 114
               Left = 227
               Bottom = 222
               Right = 378
            End
            DisplayFlags = 280
            TopColumn = 0
         End
         Begin Table = "Artists"
            Begin Extent = 
               Top = 222
               Left = 38
               Bottom = 330
               Right = 189
            End
            DisplayFlags = 280
            TopColumn = 0
         End
         Begin Table = "RecordLabel"
            Begin Extent = 
               Top = 222
               Left = 227
               Bottom = 330
               Right = 384
            End
            DisplayFlags = 280
            TopColumn = 0
         End
         Begin Table = "HD"
            Begin Extent = 
               Top = 330
               Left = 38
               Bottom = 438
               Right = 189
            End
            DisplayFlags', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'VIEW', @level1name = N'ViewMusicFull';


GO
EXECUTE sp_addextendedproperty @name = N'MS_DiagramPane2', @value = N' = 280
            TopColumn = 0
         End
      End
   End
   Begin SQLPane = 
   End
   Begin DataPane = 
      Begin ParameterDefaults = ""
      End
   End
   Begin CriteriaPane = 
      Begin ColumnWidths = 11
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
', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'VIEW', @level1name = N'ViewMusicFull';


GO
EXECUTE sp_addextendedproperty @name = N'MS_DiagramPaneCount', @value = 2, @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'VIEW', @level1name = N'ViewMusicFull';

